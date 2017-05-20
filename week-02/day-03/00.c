int FruitManipulator(int oranges, int apples, unsigned int what_to_do){
    int to_return = 0;

    if(what_to_do == 0){
        to_return = oranges + apples;
    } else {
        to_return = oranges - apples;
    }

    return to_return;
}

int main() {

    printf("%d\n", FruitManipulator(-3, 5, 1));

    return 0;
}
