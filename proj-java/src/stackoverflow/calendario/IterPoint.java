package stackoverflow.calendario;

enum IterPoint {
    IS_START(true,false), IS_END(false,true), IS_BOTH(true,true), IS_NEITHER(false,false);

    final boolean isStart;
    final boolean isEnd;

    static IterPoint make(boolean isStart, boolean isEnd){
        if(isStart)
            if(isEnd) return IterPoint.IS_BOTH;
            else return IterPoint.IS_START;
        else
            if(isEnd) return IterPoint.IS_END;
            else return IterPoint.IS_NEITHER;
    }

    IterPoint(boolean isStart, boolean isEnd){
        this.isStart = isStart;
        this.isEnd = isEnd;
    }
}
