lines = Integer(ARGV[0])
columns = Integer(ARGV[1])
fileLocation = ARGV[2]

matrix = []

lines.times do |i|
	matrix << []
	columns.times do |j|
		matrix[i] << Random.new.rand(10)
	end
end

File.open(fileLocation, "w") { |io| 
	io.write("LINHAS = #{lines}\n")
	io.write("COLUNAS = #{columns}\n")
	lines.times do |i|
		io.write("#{matrix[i].join(' ')}\n")
	end
}
