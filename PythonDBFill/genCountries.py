def generateCountries():
    f1 = open('countries of the world.csv', 'r')
    f2 = open('Countries.csv', 'w')
    l = f1.readline()
    l = f1.readline()
    n = 1
    while l:
        #print("Line = ", l)
        country_name = l[l.find("\"") + 1:l.find("\"", l.find("\"") + 1) - 1]
        line = "{0}|{1}\n".format(n, country_name)
        f2.write(line)
        #print(country_name)
        l = f1.readline()
        n = n + 1

    #print(n)
    f1.close()
    f2.close()

    print("Finished generating countries")
    return n

# generateCountries()
