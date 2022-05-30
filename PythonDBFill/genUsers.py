from faker import Faker
from random import randint
from random import choice

user_roles = ["Admin", "Tournament_Organizer", "Studio_Owner", "Team_Captain"]

def generateUsers(records_number):
    faker = Faker()
    f = open('Users.csv', 'w')
    for i in range(records_number):
        role_id = randint(1,4)
        password = "123"
        line = "{0}|{1}|{2}\n".format(role_id,
                                      faker.user_name(),
                                      password)
        f.write(line)
    f.close()
    print("Finished generating Users")

# generateUsers(1000)
