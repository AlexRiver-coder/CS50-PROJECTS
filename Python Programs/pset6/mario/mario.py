def main():
    height = int(input("Height: "))
    while (height < 1 or height > 8):
        height = int(input("Please inser a number in the range of 1 to 8: "))
    mario(height)

def mario(h):
    for x in range(h):
        o = x + 1
        n = h - x - 1
        print(" " * n, end = "")
        print("#" * o, end = "")
        print("  ", end = "")
        print("#" * o) 
        
main()