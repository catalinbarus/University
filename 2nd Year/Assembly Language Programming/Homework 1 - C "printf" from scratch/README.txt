Student: Barus Catalin-Stefan
Group: 321CD

*** IOCLA_PRINTF IMPLEMENTATION ***


** Design Idea ** :

* The Beginning *

The implementation of my printf had started from the included function
for our homework, "write_stdout". I had noticed that in order to display to 
STDOUT, write_stdout requires a char* variable in order to process the end 
result, so my main point from the beginning was to build a function that can
convert any given number to the char* format. 

That is what convert_to_string does. It also receives an integer for the base 
so the function can easily convert the number to either a decimal or hexadecimal
string as long as the number is positive. The function can't convert a negative 
number directly however, and this was a problem especially for negative 
hexadecimal numbers. 

For that case I created two functions to solve the problem: 
convert_to_binarystring and convert_bin_to_hex. The first one simply receives
a number and uses bitwise operations to convert it to binary and store the
result in a char array. The reason I chose such a specific method was to 
ensure the hex conversion could occur for numbers that would take even 32 bits
to display. I had used the size of long to bypass int's limitation of 
displaying a full 32 bit number and storing each bit in a char array was
definetely easier.

That array is then used in the second function I implemented and it is 
pretty straightforward, the previous bit char is traversed 4 by 4 bits
and for each 4 bit sequence I test the characters' behaviour and assign to a
different string its corresponding value in hexadecimal. The resulting string
is the desired conversion for a negative hexadecimal number. Also, strdup is
used to ensure no alterations occured when returning the char* array.


* The actual printf implementation *

After establishing the 3 key functions I mentioned earlier, all I had to do was
assemble them in the main printf function. I first initialiesd the obligatory
commands for reading parameters from the command line and started to traverse
them in a loop. The main idea of the implementation was to first check if the
picked parameter is a '%' since in most cases that means the next parameter 
will be a specifier. Inside the loop I increment the parameter to get to the
next readable one and verify if it falls into one of the required specifieres
for the homework. 

For all of them the general idea is the same, but I will mention any 
"specific case" implementations. For every case, I put the read number or string 
in a placeholder variable, converted that variable to a char* array and then
concatenated the string to a single final one, that will be used when calling 
write_stdout to display the proper data, just like a regular printf function
would.

For integers, since my convert_to_string function can't convert negative
numbers I turned that number to a positive one, then converted it to string as
usual and concatenated a minus at its beginning to look like a proper 
negative number.

For hexadecimals, as mentioned previously, I went through the binary to hex 
approach for negative numbers.

Additionally, for integer and unsigned specifiers, I picked the read parameter
with long to ensure no problems occured for either really big or really small
(negative) numbers and then cast them to the required data type.

After the loop I also tested most used ASCII characters, to make sure the
print function can display text too, alongside variablies and numbers/strings 
coming from a specifier. 

All of these strings are concatenated and displayed at the end when returning
the final string with write_stdout.
