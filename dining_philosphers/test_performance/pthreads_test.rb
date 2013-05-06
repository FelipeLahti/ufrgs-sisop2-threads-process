EXECUTE_TIMES = 10

def compile_pthreads
	`gcc ../pthreads/pthreads.c -o pthreads_test_performance.out`
end

def execute_it number_of_threads
	values = []
	EXECUTE_TIMES.times {
		t_init = Time.now.to_f
		`./pthreads_test_performance.out #{number_of_threads} test_files/in1.txt test_files/in2.txt`
		t_end = Time.now.to_f
		values << t_end - t_init
	}
	values
end

def get_avg list
	list.reduce(:+).to_f / list.size
end

def main
	compile_pthreads
	
	[1,2,4,8,10].each do |number_of_threads|
		avg_time = get_avg(execute_it(number_of_threads))
		puts "#{avg_time} using #{number_of_threads} threads"
	end
end

main