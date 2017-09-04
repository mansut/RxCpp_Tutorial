#include <QtCore/QCoreApplication>
#include <rx.hpp>
#include <Qlist>

#define START_FX()  printf(__FUNCTION__ "\n");

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Esempio #1: semplice observable con sottoscrizione
// 
//  - creo un observable range
//  - gli sottoscrivo una lambda OnNext e una OnComplete
// NOTA:
//  - viene eseguito subito e completamente
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
void range00()
{
    START_FX();
    auto values1 = rxcpp::observable<>::range(1, 5);
    values1.
        subscribe(
            [](int v) { printf("OnNext: %d\n", v); },
            []() { printf("OnCompleted\n"); });
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Esempio #3: usa un accumulatore (sum)
// NOTA:
//  - viene eseguito subito e completamente
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
void accumulator_sum()
{
    START_FX();
    auto values = rxcpp::observable<>::range(1, 10).sum();
    values.
        subscribe(
            [](int v) { printf("OnNext: %d\n", v); },
            []() { printf("OnCompleted\n"); });
}
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Esempio #2: creo un observable a partire da un container diverso, usando iterate
// NOTA:
//  - viene eseguito subito e completamente
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
void iterateOverList()
{
    START_FX();
    QList<int> intList;
    intList << 1 << 2 << 3 << 4 << 5;
    auto values = rxcpp::observable<>::iterate(intList);
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
void accumulator_with_reduce()
{
    START_FX();
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

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Observables particolari 
//  emits nothing
//  generates an error
//  immediately completes
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
void observableParticolari()
{
    START_FX();
    {
        auto values = rxcpp::observable<>::never<int>();
        values.
            take_until(std::chrono::steady_clock::now() + std::chrono::milliseconds(10)).
            subscribe(
                [](int v) { printf("OnNext: %d\n", v); },
                []() { printf("OnCompleted\n"); });
    }
    {
        auto values = rxcpp::observable<>::error<int>(std::runtime_error("Error from source"));
        values.
            subscribe(
                [](int v) { printf("OnNext: %d\n", v); },
                [](std::exception_ptr ep)
        {
            try { std::rethrow_exception(ep); }
            catch (const std::exception& ex) {
                printf("OnError: %s\n", ex.what());
            }
        },
                []() { printf("OnCompleted\n"); });
    }
    {
        auto values = rxcpp::observable<>::empty<int>();
        values.
            subscribe(
                [](int v) { printf("OnNext: %d\n", v); },
                []() { printf("OnCompleted\n"); });
    }
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Create an observable that emits items every specified interval of time
// NOTA: interval: Returns an observable that emits a sequential integer every specified time interval, on the specified scheduler. 
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
void emitsItemAtRegularIntervals()
{
    START_FX();
    auto start = std::chrono::steady_clock::now() + std::chrono::milliseconds(1);
    auto period = std::chrono::milliseconds(1000);
    auto values = rxcpp::observable<>::interval(start, period);
    values.
        take(3).
        subscribe(
            [](int v) { printf("OnNext: %d\n", v); },
            []() { printf("OnCompleted\n"); });
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Create an observable that emits items in the specified interval of time
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
void emitItemsInTheSpecifiedIntervalOfTime()
{
    START_FX();
    auto period = std::chrono::milliseconds(1000);
    auto values = rxcpp::observable<>::timer(period);
    values.
        take(3).
        subscribe(
            [](int v) { printf("OnNext: %d\n", v); },
            []() { printf("OnCompleted\n"); });
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    range00();

    iterateOverList();

    accumulator_sum();

    accumulator_with_reduce();

    observableParticolari();

    emitsItemAtRegularIntervals();

    emitItemsInTheSpecifiedIntervalOfTime();




}
