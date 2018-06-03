package stackoverflow.calendario;

import java.util.function.Predicate;

public interface CalendarioPredicate<T extends Chronological> extends Predicate<T>{
}
