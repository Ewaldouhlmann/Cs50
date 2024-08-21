from cs50 import get_int
size = get_int("Choose the size of the pyramid: ")
#while size is greater than 8 or smaller than 1, it asks for another input
while (size > 8 or size < 1):
    size = get_int("Choose the size of the pyramid: ")

#printing the pyramid result
for i in range(1,size+1):
    print(" "*(size-i) + "#"*i + "  " + "#"*i)

