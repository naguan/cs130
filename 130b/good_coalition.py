def main():
    testNum =  int(input())
    for i in range(testNum):
        output = 0.0
        partyNum = int(input())
        seats = [0] * partyNum
        percentages = [0] * partyNum
        for j in range(partyNum):
            s, p = input().split()
            seats[j] = int(s)
            percentages[j] = float(p)
        combo = [0.0] * 151 #all seat combination cases from no seats to all seats
        combo[0] = 1.0 #base case, dynamic programming
        for t in range(partyNum):
            for k in range(150, seats[t]-1, -1):
                combo[k] = max(combo[k], percentages[t]/100.0 * combo[k-seats[t]]) #selects the max of current seat combination or new combination, 0 means combo not reached yet or unreachable
        for l in range(76, 151): #search for max % with majority seats, cannot be done with less than majority
            output = max(output, combo[l])
        print(output * 100.0)

if __name__== "__main__":
  main()