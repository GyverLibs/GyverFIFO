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
*/

#ifndef GyverFIFO_h
#define GyverFIFO_h
template < typename TYPE, int SIZE >
class GyverFIFO {
public:
    // запись в буфер. Вернёт true при успешной записи
    bool write(TYPE newVal) {
        uint8_t i = (head + 1) % SIZE;  // положение нового значения в буфере
        if (i != tail) {         		// если есть местечко
            buffer[head] = newVal; 		// пишем в буфер
            head = i;              		// двигаем голову
            return true;
        } else return false;
    }
    
    // доступность для записи (свободное место)
    bool availableForWrite() {
        if ((head + 1) % SIZE != tail) return true;
        else return false;
    }

    // чтение из буфера
    TYPE read() {
        if (head == tail) return 0;   // буфер пуст
        TYPE val = buffer[tail];      // берём с хвоста
        tail = (tail + 1) % SIZE;     // хвост двигаем
        return val;                   // возвращаем
    }

    // возвращает крайнее значение без удаления из буфера
    TYPE peek() {
        return buffer[tail];
    }

    // вернёт количество непрочитанных элементов
    int available() {
        return (SIZE + head - tail) % SIZE;
    }

    // "очистка" буфера
    void clear() {
        head = tail = 0;
    }

private:
    TYPE buffer[SIZE];
    int head = 0, tail = 0;
};
#endif