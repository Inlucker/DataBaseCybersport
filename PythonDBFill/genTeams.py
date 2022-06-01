from faker import Faker
from random import randint
from random import choice


def genTeamName(faker):
    name = ''
    for i in range (randint(1, 2)):
        name += faker.word() + ' '
    return name.capitalize()
        

def generateTeams(records_number, countries_n, captains):
    faker = Faker()
    f = open('Teams.csv', 'w')
    for i in range(records_number):
        country_id = randint(1, countries_n)
        sponsor_id = randint(1, records_number)
        # captain_id = randint(1, records_number)
        captain_id = choice(captains)
        line = "{0}|{1}|{2}|{3}\n".format(country_id,
                                          sponsor_id,
                                          captain_id,
                                          genTeamName(faker))
        f.write(line)
    f.close()
    print("Finished generating Teams")

# generateTeams(1000, 227)
