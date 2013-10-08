#!/usr/bin/ruby

class Replace
	def initialize(input)
		@ins = {}
		input.map! do |e| e.gsub!(/\n+/, ''); end
		input.each_index do |i|
			next unless input[i].match(/\/\/#rb/)

			if input[i].start_with?('//#rbb')
				j = i
				until input[j].start_with?('//#rbe')
					j += 1
				end
				input[i..(j+1)] = replace_multiple(input[(i+1)...j], input[j][7..-1])
			elsif input[i].start_with?('//#rbi')
				j = i
				until input[j].start_with?('//#rbe')
					j += 1
				end
				@ins[input[i][7..-1].intern] = input[(i+1)...j]
				@ins[input[i][7..-1].intern].map! do |e|
					e.gsub(/^\/\/#?/, '')
				end
				input[i..j] = nil
			elsif input[i].match(/\/\/#rbl/)
				p = (input[i] =~ /\/\/#rb/)
				input[i] = replace_line(input[i][0...p], input[i][(p + 7)..-1])
			end
		end

		puts input.join("\n")
	end

	def replace_line(line, inst)
		if inst.start_with?(':')
			return eval(@ins[inst[1..-1].intern].join("\n"))
		else
			return eval(inst)
		end
	end

	def replace_multiple(lines, inst)
		if inst.start_with?(':')
			return eval(@ins[inst[1..-1].intern].join("\n"))
		else
			return eval(inst)
		end
	end
end

input = []
ARGF.each do |line|
	input << line
end

Replace.new(input)

