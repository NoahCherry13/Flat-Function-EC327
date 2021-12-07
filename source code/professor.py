
class Professor:
    def __init__(self, ratemyprof_id: int, first_name: str, last_name: str, num_of_ratings: int, overall_rating, dept: str):
        self.ratemyprof_id = ratemyprof_id
        self.department = dept
        self.name = f"{first_name} {last_name}"
        self.first_name = first_name
        self.last_name = last_name
        self.num_of_ratings = num_of_ratings

        if self.num_of_ratings < 1:
            self.overall_rating = 0

        else:
            self.overall_rating = float(overall_rating)
