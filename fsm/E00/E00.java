/*
Copyright (C) 2019 Artyom V. Poptsov <poptsov.artyom@gmail.com>

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
*/


/**
 * Пример реализации детерминированного конечного автомата (ДКА), удаляющего
 * однострочные комментарии из входного потока данных. Данные беруться из
 * стандартного потока ввода (stdin) и выводятся в стандартный поток вывода
 * (stdout).
 *
 * Компиляция:
 *   $ javac E00.java
 *
 * Пример запуска с подачи текста самой же программы на обработку:
 *   $ cat E00.java | java E00
 */
public class E00 {
    // Возможные состояние конечного автомата
    static final int DEFAULT       = 0;
    static final int CHECK_COMMENT = 1;
    static final int SKIP_COMMENT  = 2;

    public static void main(String[] args) throws Exception {
        int ch;
        int state = DEFAULT;
        while ((ch = System.in.read()) != -1) {
            switch (state) {
            case DEFAULT:
                if (ch == '/') {
                    state = CHECK_COMMENT;
                } else {
                    System.out.print((char) ch);
                }
                break;
            case CHECK_COMMENT:
                if (ch == '/') {
                    state = SKIP_COMMENT;
                } else {
                    System.out.print("/" + (char) ch);
                    state = DEFAULT;
                }
                break;
            case SKIP_COMMENT:
                if (ch == '\n') {
                    System.out.print('\n');
                    state = DEFAULT;
                }
            }
        }
    }
}
