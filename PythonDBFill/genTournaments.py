from faker import Faker
from random import randint


def genTeamName(faker):
    name = ''
    for i in range(randint(1, 2)):
        name += faker.word() + ' '
    return name.capitalize()
    # return faker.word().capitalize()


def generateTournaments(records_number, countries_n):
    faker = Faker()
    f = open('Tournaments.csv', 'w')
    for i in range(records_number):
        country_id = randint(1, countries_n)
        organizer_id = randint(1, records_number)
        name = genTeamName(faker)
        prize_pool = randint(100000, 10000000)
        line = "{0}|{1}|{2}|{3}\n".format(country_id,
                                          organizer_id,
                                          name,
                                          prize_pool)
        f.write(line)
    f.close()
    print("Finished generating Tournaments")


# generateTournaments(1000, 227)
