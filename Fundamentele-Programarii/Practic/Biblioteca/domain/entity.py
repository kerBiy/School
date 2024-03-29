class Book:
    def __init__(self, id: int, title: str, author: str, year: int) -> None:
        self.__id = id
        self.__title = title
        self.__author = author
        self.__year = year

    def __str__(self) -> str:
        return f"{self.id}, {self.title}, {self.author}, {self.year}"

    def __eq__(self, other: object) -> bool:
        return (
            self.id == other.id
            and self.title == other.title
            and self.author == other.author
            and self.year == other.year
        )

    @property
    def id(self) -> int:
        return self.__id

    @property
    def title(self) -> str:
        return self.__title

    @property
    def author(self) -> str:
        return self.__author

    @property
    def year(self) -> int:
        return self.__year

    @author.setter
    def author(self, new_author: str) -> None:
        self.__author = new_author
