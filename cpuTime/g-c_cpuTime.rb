#coding:utf-8
require 'open3'


def calcLoop(num)
	n = ' ' + num

	print("gauss_s", num, "\n")
	gauss_s, stdout, stderr = Open3.capture3("./gss" + n)
	puts("=============================================================")
	print("\n\n")

	File.open("gauss_s_result", "a") do |file|
		file.puts gauss_s
	end



	print("cg", num, "\n")
	cg, stdout, stderr 		= Open3.capture3("./cg" + n)
	puts("=============================================================")
	print("\n\n")

	File.open("cg_result", "a") do |file|
		file.puts cg
	end


	# print("gauss", num, "\n")
	# gauss, stdout, stderr = Open3.capture3("./gs" + n)
	# puts("=============================================================")
	# print("\n\n")

	# File.open("gauss_result", "a") do |file|
	# 	file.puts gauss
	# end


	# print("jacob", num, "\n")
	# jacob, stdout, stderr 	= Open3.capture3("./jb" + n)
	# puts("=============================================================")
	# print("\n\n")

	# File.open("jacob_result", "a") do |file|
	# 	file.puts jacob
	# end

end


puts("MIN")
MIN = gets().chomp.to_i

puts("MAX")
MAX = gets().chomp.to_i

puts("DISTANCE")
DISTANCE = gets().chomp.to_i

p Open3.capture3("rm *_result")


# p Open3.capture3("gcc cpu_gauss.c -o gs")
# p Open3.capture3("gcc cpu_jacob.c -o jb")
p Open3.capture3("gcc cpu_gauss_s.c -o gss")
p Open3.capture3("gcc cpu_cg.c -o cg")


MIN.step(MAX, DISTANCE) { |num|
	calcLoop(num.to_s)
}



Open3.popen3("gnuplot") do |gin, gout, ger|
	gin.puts "set terminal png font \"ヒラギノ明朝 Pro W3.otf\""
	gin.puts "set output \"cpu_time.png\""
	gin.puts "set title \"計算速度比較\""
	gin.puts "set xlabel '次元数 N'"
	gin.puts "set ylabel 'CPU Time(sec)'"
	gin.puts "plot \"gauss_s_result\" w l, \"cg_result\" w l"
	
	puts('Create Grapsh Successed')
end

Open3.capture3("rm gs jb cg gss")


