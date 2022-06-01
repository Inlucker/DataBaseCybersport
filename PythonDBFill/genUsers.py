from faker import Faker
from random import randint
from random import choice

user_roles = ["Admin", "Tournament_Organizer", "Studio_Owner", "Team_Captain"]

def generateUsers(records_number):
    faker = Faker()
    organizers = []
    owners = []
    captains = []
    f = open('Users.csv', 'w')
    for i in range(records_number):
        role_id = randint(2,4)
        if (role_id == 2):
            organizers.append(i+1)
        elif (role_id == 3):
            owners.append(i+1)
        elif (role_id == 4):
            captains.append(i+1)
        password = "123"
        line = "{0}|{1}|{2}\n".format(role_id,
                                      faker.user_name(),
                                      password)
        f.write(line)
    f.close()
    print("Finished generating Users")
    return organizers, owners, captains

# generateUsers(1000)
