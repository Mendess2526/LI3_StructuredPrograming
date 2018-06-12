package engine.calendario;

/**
 * Enum que define o ponto de iteração do calendário.
 */
enum IterPoint {
    /** Está no início da iteração. */
    IS_START(true,false),
    /** Está no fim da iteração. */
    IS_END(false,true),
    /** Está no início e no fim da iteração. */
    IS_BOTH(true,true),
    /** Não está no início nem no fim. */
    IS_NEITHER(false,false);

    /** {@code true} se estiver pelo menos no início, {@code false} caso contrário. */
    final boolean isStart;
    /** {@code true} se estiver pelo menos no fim, {@code false} caso contrário. */
    final boolean isEnd;

    /**
     * Cria uma instância do enum a partir de 2 booleans.
     * @param isStart Se está no início da iteração.
     * @param isEnd Se está no fim da iteração.
     * @return {@code IS_START} se for passado {@code (true, false)}
     *         {@code IS_END} se for passado {@code (false,true)}
     *         {@code IS_BOTH} se for passado {@code (true, true)}
     *         {@code IS_NEITHER} se for passado {@code (false, false)}.
     */
    static IterPoint make(boolean isStart, boolean isEnd){
        if(isStart)
            if(isEnd) return IterPoint.IS_BOTH;
            else return IterPoint.IS_START;
        else
            if(isEnd) return IterPoint.IS_END;
            else return IterPoint.IS_NEITHER;
    }

    /**
     * Construtor do enum.
     * @param isStart Se está no início da iteração.
     * @param isEnd Se está no fim da iteração.
     */
    IterPoint(boolean isStart, boolean isEnd){
        this.isStart = isStart;
        this.isEnd = isEnd;
    }
}
