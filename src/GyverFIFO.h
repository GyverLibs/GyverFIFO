/*
    Лёгкий универсальный кольцевой буфер для Arduino
    Документация: 
    GitHub: https://github.com/GyverLibs/GyverFIFO
    Возможности:
    - Чтение, запись, очистка
    - Статический размер
    - Выбор типа данных
    
    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License

    Версии:
    v1.0 - релиз
    v1.1 - исправлено переполнение при >255 элементов
*/

#ifndef _GyverFIFO_h
#define _GyverFIFO_h
template < typename TYPE, int SIZE >
class GyverFIFO {
public:
    // запись в буфер. Вернёт true при успешной записи
    bool write(TYPE newVal) {
        if (count < SIZE) {                           // если буфер не переполнен
            buffer[(head + count++) % SIZE] = newVal; // пишем в конец очереди и увеличиваем количество
            return 1;
        } else return 0;
    }
    
    // доступность для записи (свободное место)
    bool availableForWrite() {
        return count < SIZE;
    }

    // чтение из буфера. Если буфер пуст, поведение не определено
    TYPE read() {
        TYPE val = buffer[head];          // берём с головы
        if (count) {                      // если очередь не пуста
            head = (head + 1) % SIZE;     // голову двигаем
            count--;                      // уменьшаем количество
        }
        return val;                       // возвращаем
    }

    // возвращает крайнее значение без удаления из буфера
    TYPE peek() {
        return buffer[head];
    }

    // вернёт количество непрочитанных элементов
    int available() {
        return count;
    }

    // "очистка" буфера
    void clear() {
        count = 0;
    }

private:
    TYPE buffer[SIZE];
    int head = 0, count = 0;
};
#endif