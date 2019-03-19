struct S
{
    int (*member)(int);
};

int f(int i)
{
    return ++i;
}

int main(int argc, const char *argv[])
{
    S s;
    s.member = &f;
    return s.member(2);
    return 0;
}
