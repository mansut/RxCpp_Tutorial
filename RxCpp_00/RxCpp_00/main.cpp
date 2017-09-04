#include <QtCore/QCoreApplication>
#include <rx.hpp>
#include <Qlist>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // Esempio #1: semplice observable con sottoscrizione
    // 
    //  - creo un observable range
    //  - gli sottoscrivo una lambda OnNext e una OnComplete
    // NOTA:
    //  - viene eseguito subito e completamente
    //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    {
        auto values1 = rxcpp::observable<>::range(1, 5);
        values1.
            subscribe(
                [](int v) { printf("OnNext: %d\n", v); },
                []() { printf("OnCompleted\n"); });
    }

    //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // Esempio #2: creo un observable a partire da un container diverso, usando iterate
    // NOTA:
    //  - viene eseguito subito e completamente
    //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    {
        QList<int> intList;
        intList << 1 << 2 << 3 << 4 << 5;
        auto values = rxcpp::observable<>::iterate(intList);
        values.
            subscribe(
                [](int v) { printf("OnNext: %d\n", v); },
                []() { printf("OnCompleted\n"); });

    }


    //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // Esempio #3: usa un accumulatore (sum)
    // NOTA:
    //  - viene eseguito subito e completamente
    //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    {
        auto values = rxcpp::observable<>::range(1, 10).sum();
        values.
            subscribe(
                [](int v) { printf("OnNext: %d\n", v); },
                []() { printf("OnCompleted\n"); });
    }
    //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // Esempio #3: accumalore somma fatto con reduce
    // NOTA:
    //  - viene eseguito subito e completamente
    //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    {
        auto values = rxcpp::observable<>::range(1, 7).
            reduce(
                0,  // valore iniziale
                [](int currentSum, int v)   // accumulator function to be invoked on each item 
        {
            currentSum += v;
            return currentSum;
        },
                [](int theSum)  // result producing function that makes the final value from the last accumulator call result
        {
            return theSum;
        });

        values.
            subscribe(
                [](int v) { printf("OnNext: %d\n", v); },
                []() { printf("OnCompleted\n"); });
    }
}
