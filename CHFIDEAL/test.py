import random


class Doors(set):

    def __init__(self, options):
        super().__init__(options)
        self.opened = set()

    def choice(self):
        options = list(self)
        chosen = random.choice(options)
        return chosen

    def open_choice(self):
        chosen = self.choice()
        self.open(chosen)
        return chosen

    def open(self, door):
        self.remove(door)
        self.opened.add(door)

    def close(self, door):
        self.opened.remove(door)
        self.add(door)


class Chooser:

    def __init__(self, doors: Doors):
        self.doors = doors
        self.door = self.doors.open_choice()

    def change_door(self):
        other = self.doors.open_choice()

        self.doors.close(self.door)
        self.door = other
        return other

    def chosen(self):
        return self.door


class Grader:

    def __init__(self, doors: Doors):
        self.doors = doors
        self.prize = self.doors.choice()

    def open_door(self):
        prize_chosen = self.prize not in self.doors

        self.doors.discard(self.prize)
        opened = self.doors.open_choice()
        if not prize_chosen:
            self.doors.add(self.prize)

        return opened

    def has_prize(self, door):
        return door == self.prize
