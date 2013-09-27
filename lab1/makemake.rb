#!/usr/bin/ruby

class Node
	attr_reader :ID, :nodes, :incs, :libs, :is_main
	@@gnodes = {}
	@@libraryflags = {:math => '-lm'}

	def initialize(fn)
		@ID = fn.intern
		@nodes = [self]
		@incs = []
		@libs = []
		@is_main = false
		@@gnodes[@ID] = self

		File.open("#{fn}.c", 'r') do |file|
			cont = file.read
			cont += File.read("#{fn}.h") if File.exist?("#{fn}.h")
			cont.gsub!(/[\r\n]+/, "\n")

			cont.each_line do |line|
				@is_main = true if line.match(/^[^\/]*(int|void)[ \t]+main\(.*\)/)
				next if not line.match(/[ \t]*#include/)

				line.gsub!(/^[ \t]*#include[ \t]+([\"<][\w^\.]+\.h[\">])[.\n]*$/, '\1')

				if line.match(/^\"#{fn}.h\"$/)
				elsif line.match(/^<.*>$/)
					line.gsub!(/^<([\w^\.]+)\.h>$/, '\1')
					@libs << @@libraryflags[line.intern] if @@libraryflags.key?(line.intern)
				else
					line.gsub!(/^\"([\w^\.]+)\.h\"$/, '\1')
					if File.exist?("#{line}.c")
						@nodes << @@gnodes[line.intern] or Node.new(line)
					else
						@incs << "#{line}.h"
					end
				end
			end
		end
	end

	def get_libs(libs = [], v = [])
		v << self
		nodes.each do |node|
			next if node.nil? or v.include?(node)
			node.get_libs(libs, v);
		end

		return libs.concat(@libs).uniq
	end
end

class Main
	@@defflags = '-Wall -g -O0 -Wno-psabi'

	def initialize(flags = @@defflags)
		@nodes = []

		Dir.foreach('.') do |file|
			next if not file.end_with?('.c')

			@nodes << Node.new(file.gsub(/\.c$/, ''))
		end

		result = "CC=cc\nCFLAGS=#{flags}\n\n"
		body = ""
		all = []

		@nodes.each do |node|
			fnl = "#{node.ID.to_s}: "
			os = print_node(node.nodes).join('.o ') + '.o'
			libs = node.get_libs.join(' ');
			fnl += "#{os}\n\t$(CC) $(CFLAGS) #{os} -o #{node.ID.to_s} #{libs}\n\n"

			obj = "#{node.ID.to_s}.o: #{node.ID.to_s}.c "
			node.incs.each do |i|
				obj += "#{i} "
			end
			obj += "\n\t$(CC) $(CFLAGS) -c #{node.ID.to_s}.c -o #{node.ID.to_s}.o\n\n"

			body += obj
			body += fnl if node.is_main 
			all << node.ID.to_s if node.is_main
		end

		result += "all: #{all.join(' ')}\n\n#{body}\nclean:\n\trm -f *.o\n\nremove: clean\n\t"
		result += 'find -executable | sed -n -e \'/\.\// s/^\.\///\' -e \'/^lab/ p\' | xargs rm -f' + "\n"

		puts result
	end

	def print_node(nodes, r = [])
		nodes.each do |node|
			next if node.nil? or r.include?(node.ID.to_s)
			r << node.ID.to_s
			print_node(node.nodes, r)
		end

		return r
	end
end

Main.new

