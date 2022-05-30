def generateUserRoles():
    f = open('UserRoles.csv', 'w')
    f.write("1|Admin")
    f.write("2|Tournament_Organizer")
    f.write("3|Studio_Owner")
    f.write("4|Team_Captain")

    f.close()
    print("Finished generating Roles")

# generateUserRoles()