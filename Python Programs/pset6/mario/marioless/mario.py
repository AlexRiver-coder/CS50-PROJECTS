def main():

    # Inflinite loop to check if the user inputs a valid number
    # If the user does not cooperate re prompt
    while True:
        try:
            height = int(input("Height: "))
            if(height > 0 and height < 9):
                mario(height)
                break
        except Exception:
            print("invalid number in range of 1 to 8")

            
# True function that generates the pyramid
def mario(h):
    for x in range(h):
        o = x + 1
        n = h - x - 1
        print(" " * n, end="")
        print("#" * o)
        
        
main()