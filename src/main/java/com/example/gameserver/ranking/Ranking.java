package com.example.gameserver.ranking;

import org.hibernate.annotations.GenericGenerator;

import javax.persistence.*;
import java.util.Objects;

@Entity
@Table(name = "RANKING")
public class Ranking {
    @GenericGenerator(
            name = "userSequenceGenerator",
            strategy = "org.hibernate.id.enhanced.SequenceStyleGenerator",
            parameters = {
                    @org.hibernate.annotations.Parameter(name = "sequence_name", value = "userSequence"),
                    @org.hibernate.annotations.Parameter(name = "initial_value", value = "2000"),
                    @org.hibernate.annotations.Parameter(name = "increment_size", value = "1")
            }
    )
    @Id
    @GeneratedValue(generator = "userSequenceGenerator")
    @Column(name = "ID", nullable = false)
    private Long id;

    @Column(name = "NAME")
    private String name;
    @Column(name = "BASE")
    private Integer base;
    @Column(name = "FORMULA")
    private String formula;

    public Ranking() {
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Ranking ranking = (Ranking) o;
        return id.equals(ranking.id) && name.equals(ranking.name) && base.equals(ranking.base) && formula.equals(ranking.formula);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, name, base, formula);
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Integer getBase() {
        return base;
    }

    public void setBase(Integer base) {
        this.base = base;
    }

    public String getFormula() {
        return formula;
    }

    public void setFormula(String formula) {
        this.formula = formula;
    }

    public Ranking(Long id, String name, Integer base, String formula) {
        this.id = id;
        this.name = name;
        this.base = base;
        this.formula = formula;
    }
}
