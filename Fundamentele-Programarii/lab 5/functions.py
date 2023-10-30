from validator import already_exists


def add_expense(expenses: list[dict], expense: dict) -> None:
    if already_exists(expenses, expense):
        raise Exception("Already exists in the list.")

    expenses.append(expense)
