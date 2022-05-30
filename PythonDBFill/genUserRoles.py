def generateUserRoles():
    f = open('UserRoles.csv', 'w')
    f.write("1|Admin\n")
    f.write("2|Tournament_Organizer\n")
    f.write("3|Studio_Owner\n")
    f.write("4|Team_Captain\n")

    f.close()
    print("Finished generating Roles")

# generateUserRoles()
