#!/usr/bin/ruby

Dir('.').each do |f|
	next unless f.end_with?('.c')

	`./conv #{f} > _W_#{f}`
end

