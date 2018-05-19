package stackoverflow.calendario;

interface CalendarioPredicate<T> {
    boolean apply(Chronological elem);
}
