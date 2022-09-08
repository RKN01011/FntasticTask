from collections import defaultdict


def convert_string(value: str) -> str:
    """
    Цель - конвертировать исходную строку, в новую строку, где каждый символ заменяется на символ
    “ ( ”, если символ встречается только один раз или на “ ) “, если символ встречается больше одного раза.
    При решении программа должна игнорировать заглавные буквы
    при определении дубликатов (т.е. “А” и “а” - это один и тот же символ).
    Пример входных и выходных данных:
    "din"      =>  "((("
    "recede"   =>  "()()()"
    "Success"  =>  ")())())"
    "(( @"     =>  "))(("

    Преставленое решение имеет сложность o(n + n + n)
    """

    count, old_str, new_str = defaultdict(lambda: 0), value.lower(), ''

    for char in old_str:
        count[char] = count.setdefault(char, 0) + 1
    for i in old_str:
        new_str += '(' if count[i] == 1 else ')'

    return new_str


print(
    ' "din" => ' + convert_string('din') + '\n',
    '"recede" => ' + convert_string('recede') + '\n',
    '"Success"  => ' + convert_string('Success') + '\n',
    '"(( @" => ' + convert_string('(( @')
)
