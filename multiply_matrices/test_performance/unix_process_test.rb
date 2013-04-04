EXECUTE_TIMES = 10

def compile_unix_process
	`gcc ../unix_process/app_unix_process.c -o unix_process_test_performance.out`
end

def execute_it number_process
	values = []
	EXECUTE_TIMES.times {
		t_init = Time.now.to_f
		`./unix_process_test_performance.out #{number_process} test_files/in1.txt test_files/in2.txt`
		t_end = Time.now.to_f
		values << t_end - t_init
	}
	values
end

def get_avg list
	list.reduce(:+).to_f / list.size
end

def main
	compile_unix_process
	
	[1,2,4,8,10].each do |process_number|
		avg_time = get_avg(execute_it(process_number))
		puts "#{avg_time} using #{process_number} process"
	end
end

main