import cs50


def main():
    text = cs50.get_string("Text: ")
    qt_spaces, qt_letters, qt_sentences = get_text_info(text)
    grade = round(get_grade(qt_spaces, qt_letters, qt_sentences))

    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


def get_text_info(text):
    spaces = 1
    letters = 0
    sentences = 0
    for i in range(0, len(text)):
        if spaces == 100:
            break
        else:
            if text[i] == ' ':
                spaces += 1
            elif text[i].isalpha():
                letters += 1
            elif text[i] == '.' or text[i] == '?' or text[i] == '!':
                sentences += 1
    return spaces, letters, sentences


def get_grade(qt_spaces, qt_letters, qt_sentences):
    aver_letter = qt_letters/qt_spaces * 100
    aver_sent = qt_sentences/qt_spaces * 100

    idx = 0.0588 * aver_letter - 0.296 * aver_sent - 15.8
    return idx


main()
