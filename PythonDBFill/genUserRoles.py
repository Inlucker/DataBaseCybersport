def generateUserRoles():
    f = open('UserRoles.csv', 'w')
    f.write("1|admin\n")
    f.write("2|tournament_organizer\n")
    f.write("3|studio_owner\n")
    f.write("4|team_captain\n")

    f.close()
    print("Finished generating UserRoles")

# generateUserRoles()
