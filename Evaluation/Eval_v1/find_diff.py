# Author: Wei Wei
# Last edited: 8/24/2022
# Email: iamdoublewei@gmail.com
#
# export memory values from CCS
# CCS -> View -> Memory Browser
# Format: 16-Bit Unsigned Int
# Start Address: 0
# Length -> Specify the number of memory words to read: 524288 (read all memory)
# One word = 16 bits, each memory address contains 8 bits data
# each line contains 2 memory address
# compare the differece between 2 versions
print("Comparing files ", " @ " + 'file1.txt', " # " + 'file2.txt', '', sep='\n')

# the output line number need to exclude margin to get the right memory address
margin = 2
file_1 = open('v1.dat')
file_2 = open('v2.dat')    
file_1_line = file_1.readline()
file_2_line = file_2.readline()

# Use as a COunter
line_no = 1

print("Differences")
while file_1_line != '' or file_2_line != '':

	# Removing whitespaces
	file_1_line = file_1_line.rstrip()
	file_2_line = file_2_line.rstrip()

	# Compare the lines from both file
	if file_1_line != file_2_line:
		address = (line_no - margin) * 2
		# otherwise output the line on file1 and use @ sign
		if file_1_line == '':
			print("@line", line_no, "Address:%d" % address, file_1_line)
		else:
			print("@line-", line_no, "Address:%d" % address, file_1_line)
			
		# otherwise output the line on file2 and use # sign
		if file_2_line == '':
			print("#line", line_no, "Address:%d" % address, file_2_line)
		else:
			print("#line+", line_no, "Address:%d" % address, file_2_line)

		# Print a empty line
		print()

	# Read the next line from the file
	file_1_line = file_1.readline()
	file_2_line = file_2.readline()

	line_no += 1

file_1.close()
file_2.close()
