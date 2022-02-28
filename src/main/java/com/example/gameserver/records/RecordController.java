package com.example.gameserver.records;

import org.springframework.format.annotation.DateTimeFormat;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.net.URI;
import java.net.URISyntaxException;
import java.util.Date;
import java.util.List;

@RestController
@RequestMapping("records")
public class RecordController {
    private final RecordRepository recordRepository;

    public RecordController(RecordRepository recordRepository) {
        this.recordRepository = recordRepository;
    }

    @GetMapping
    public List<Record> getRecords(@RequestParam(name="sort") Boolean sort,
                                @RequestParam(name="game") Long gameId) {
        if (sort) // if true sorts from newest to oldest
            return recordRepository.findByGameIdOrderByDateDesc(gameId);
        else
            return recordRepository.findByGameIdOrderByDateAsc(gameId);
    }

    @GetMapping(path = "/query")
    public List<Record> getRecordsQuery(@RequestParam(name="sort") Boolean sort,
                                        @RequestParam(name="game") Long gameId,
                                        @RequestParam(name="draw", required = false) Boolean draw,
                                        @RequestParam(name="oneWin", required = false) Boolean oneWin,
                                        @RequestParam(name="twoWin", required = false) Boolean twoWin,
                                        @RequestParam(name="minDate", required = false)
                                        @DateTimeFormat(iso = DateTimeFormat.ISO.DATE) Date dateBeg,
                                        @RequestParam(name="maxDate", required = false)
                                        @DateTimeFormat(iso = DateTimeFormat.ISO.DATE) Date dateEnd,
                                        @RequestParam(name="nickOne", required = false) String nickOne,
                                        @RequestParam(name="nickTwo", required = false) String nickTwo) {
        long lDraw = -1L, lOneWin = -1L, lTwoWin = -1L;
        if (draw == null || draw) lDraw = 0L;
        if (oneWin == null || oneWin) lOneWin = 1L;
        if (twoWin == null || twoWin) lTwoWin = 2L;
        if (dateBeg == null) dateBeg = new Date(0);
        if (dateEnd == null) dateEnd = new Date(System.currentTimeMillis());
        if (nickOne == null) nickOne = "";
        if (nickTwo == null) nickTwo = "";

        if (sort) // if true sorts from newest to oldest
return recordRepository.findByQueryDesc(lDraw, lOneWin, lTwoWin, gameId, dateBeg, dateEnd, nickOne, nickTwo);
        else
return recordRepository.findByQueryAsc(lDraw, lOneWin, lTwoWin, gameId, dateBeg, dateEnd, nickOne, nickTwo);
    }

    @PostMapping
    public ResponseEntity<?> createRecord(@RequestBody Record record) throws URISyntaxException {
        Record savedRecord = recordRepository.save(record);
        return ResponseEntity.created(new URI("/records/" + savedRecord.getId())).body(savedRecord);
    }
}
