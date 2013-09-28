#!/usr/bin/ruby

class Node
	attr_reader :ID, :incs, :libs, :deps, :exec
	@@libraries = {:math => '-lm'}
	@@cflags = '-Wall -g -O0 -Wno-psabi'

	def initialize(fn)
		@ID = fn
		@incs, @libs = get_incs(fn)
		@incs, @deps = make_dependencies(@incs)
		@exec = is_executable?(fn)
	end

	def make_dependencies(incs)
		cf = []
		hf = []

		incs.each do |file|
			if file.end_with?('.c')
				cf << file
			elsif file.end_with?('.h')
				file.gsub!(/\.h$/, '')

				hf << "#{file}.h"
				cf << "#{file}.c" if File.exist?("#{file}.c")
			end
		end

		return [hf, cf]
	end

	def get_incs(fn, fs = [], ls = [])
		if not fs.include?(fn)
			fs << fn
	
			File.read(fn).each_line do |line|
				next if not line.match(/^[ \t]*#include/)
				
				line.gsub!(/^[ \t]*#include[ \t]+([\"<].+\.h[\">])[.\n]*$/, '\1')
	
				if line.match(/^<.*>$/)
					line.gsub!(/^<(.*)\.h>$/, '\1')
					ls << @@libraries[line.intern] if @@libraries.key?(line.intern)
				elsif line.match(/^\".*\"$/)
					line.gsub!(/^\"(.*)\"$/, '\1')
					fs, ls = get_incs(line, fs, ls)
				end
			end
		end

		return [fs.uniq, ls.uniq] 
	end

	def is_executable?(fn)
		line1 = File.read(fn)
		line2 = line1.gsub(/\/\*[.\n]*?\*\//, '')
		lines = line2.split(/\n/)

		lines.each_index do |i|
			lines[i].gsub!(/([^\\])\"[.^\"]*?[^\\]\"/, '\1')
			lines[i].gsub!(/\/\/.*$/, '')

			return true if lines[i].match(/(int|void)[ \t]+main\(.*\)/)
		end

		return false
	end

	def self.build(flags = @@cflags)
		head = "CC=cc\nCFLAGS=#{flags}\n\n"
		obj = ""
		exec = ""
		all = []

		Dir.foreach('.') do |file|
			next if not file.end_with?('.c')

			node = Node.new(file)

			obj += "#{node.ID}.o: #{node.ID} #{node.incs.join(' ')}\n\t$(CC) $(CFLAGS) -c #{node.ID} -o #{node.ID}.o\n\n".gsub(/ +/, ' ')

			if(node.exec)
				os = node.deps.join('.o ') + '.o' 
				exec += "#{node.ID[0..-3]}: #{os}\n\t$(CC) $(CFLAGS) #{os} -o #{node.ID[0..-3]} #{node.libs.join(' ')}\n\n".gsub(/ +/, ' ')
				all << node.ID[0..-3]
			end
		end

		head += "all: #{all.join(' ')}\n\n#{exec}\n#{obj}\nclean:\n\trm -f *.o\n\nremove: clean\n\t".gsub(/ +/, ' ')
		head += 'find -executable | sed -n \'/^\.\/lab[^\.]*$$/ p\' | xargs rm -f' + "\n\n"

		puts head
	end
end

Node.build

