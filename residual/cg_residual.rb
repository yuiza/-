#coding:utf-8
require 'open3'


puts("N * N にしますか")
num = gets().chomp

# p Open3.capture3("gcc jacob.c -o jb")
p Open3.capture3("gcc gauss_s.c -o gs")
p Open3.capture3("gcc cg.c -o cg")

n = ' ' + num

# cg, stdout, stderr 		= Open3.capture3("./cg" + n)

# print("gauss_s\n")

gauss_s, stdout, stderr = Open3.capture3("./gs" + n)

puts("=============================================================")
puts('gauss_s calc end!')
puts("=============================================================")
print("\n\n")
# puts("=============================================================")
# print("jacob\n")

# jacob, stdout, stderr 	= Open3.capture3("./jb" + n)

# puts("=============================================================")
# puts('jacob calc end!')
# print("\n\n")
# puts("=============================================================")
# print("cg\n")

cg, stdout, stderr 		= Open3.capture3("./cg" + n)

puts("=============================================================")
puts('cg calc end!')
puts("=============================================================")
print("\n\n")

File.write('gauss_s_reslut2', gauss_s)
# File.write('jacob', jacob)
File.write('cg_result2', cg)

Open3.popen3("gnuplot") do |gin, gout, ger|
	gin.puts "set terminal png font \"ヒラギノ明朝 Pro W3.otf\""
	gin.puts "set output \"gss-cg_residual.png\""
	 gin.puts "set format y \"10^{%L}\""
	# gin.puts "set xtics 1"
	# gin.puts "set xrange[0:10]"
	# gin.puts "set yrange[-100:]"
	gin.puts "set title \"N=" + num + "の残差履歴\""
	gin.puts "set xlabel '反復回数'"
	gin.puts "set ylabel '残差'"
	gin.puts "plot \"cg_result2\" w l, \"gauss_result2\" w l"
	puts('Create Grapsh Successed')
end

Open3.capture3("rm gs jb cg")


