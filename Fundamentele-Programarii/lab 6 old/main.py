from tests import test_functions
from utils import print_expenses, update_history, clear_screen

from ui.adding import add_submenu
from ui.deleting import delete_submenu
from ui.searching import search_submenu
from ui.printing import print_submenu
from ui.filtering import filter_submenu
from ui.undoing import undo


def option_menu() -> None:
    print("\n\nOPTION MENU:")
    print("Enter 0 for showing the expenses list")
    print("Enter 1 for add menu")
    print("Enter 2 for delete menu")
    print("Enter 3 for search menu")
    print("Enter 4 for print menu")
    print("Enter 5 for filter menu")
    print("Enter z for Undo")
    print("Enter q for Exiting the program")


def console_application() -> None:
    expenses = []
    history = [[]]

    options = {
        0: print_expenses,
        1: add_submenu,
        2: delete_submenu,
        3: search_submenu,
        4: print_submenu,
        5: filter_submenu,
    }

    while True:
        option_menu()
        user_input = input("\nEnter an option: ")
        clear_screen()

        if user_input == "q":
            print("Exiting the program...")
            break

        if user_input == "z":
            undo(expenses, history)

        else:
            try:
                user_input = int(user_input)
                options[user_input](expenses)
                update_history(expenses, history)

            except ValueError:
                print("Invalid input.")
            except KeyError:
                print("This option is not yet implemented.")


if __name__ == "__main__":
    test_functions()
    console_application()
