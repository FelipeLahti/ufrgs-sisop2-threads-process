require "fileutils"
TEST_DIRS = ["test", "unix_process/test", "pthreads/test"];

def compile file
	response = system "gcc #{file} -o out_test/#{File.basename(file)}.out"
	["#{file}.out", response]
end

def run_one_test file
	FileUtils.cd "out_test"
	puts `./#{File.basename(file)}`
	FileUtils.cd "../"
end

def clean_up
	FileUtils.rm_rf "out_test/*.out"
end

def run_tests 
	TEST_DIRS.each do |test_dir|
		#puts "Starting test suite '#{test_dir}'"
		Dir["#{test_dir}/*_test.c"].each do |test_file|
			unless test_file.match 'template'
				#puts "Starting test '#{test_file}'"
				file = compile test_file
				if file[1]
					run_one_test file[0]
				else
					puts "Fail to compile #{file[0]}" 
				end
			end
		end
	end
end

clean_up
run_tests