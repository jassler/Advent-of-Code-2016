package main

import (
	"flag"
	"fmt"
	"time"
)

// Generator contains its current value and takes care of calculating the next one
type Generator struct {
	value      uint64
	factor     uint64
	div        uint64
	multipleOf uint64
}

// Calculate next value in sequence.
func (g *Generator) next() uint64 {
	// keep calculating until we find a number with a factor of 4 or 8
	for g.value = (g.value * g.factor) % g.div; g.value%g.multipleOf != 0; g.value = (g.value * g.factor) % g.div {
	}

	return g.value
}

// go function to find generated values
func findValidValues(c chan uint64, generator *Generator) {
	for {
		c <- generator.next()
	}
}

// calculate pairs using channels
func calculateConcurrently(genA, genB *Generator, buffer int) int {

	a := make(chan uint64, buffer)
	b := make(chan uint64, buffer)

	go findValidValues(a, genA)
	go findValidValues(b, genB)

	count := 0

	for index := 0; index < 5000000; index++ {

		if (<-a % 0x10000) == (<-b % 0x10000) {
			count++
		}

	}

	return count
}

// calculate pairs without channels, straight up sequentially
func calculateSequentially(genA, genB *Generator) int {
	count := 0

	for index := 0; index < 5000000; index++ {

		if (genA.next() % 0x10000) == (genB.next() % 0x10000) {
			count++
		}

	}

	return count
}

func main() {

	test := flag.Bool("test", false, "Use test variables")
	buffer := flag.Int("buffer", -1, "How many values to buffer in channels. If set to -1, calculate sequentially.")
	flag.Parse()

	genA := &Generator{
		value:      512,
		factor:     16807,
		div:        2147483647,
		multipleOf: 4,
	}

	genB := &Generator{
		value:      191,
		factor:     48271,
		div:        2147483647,
		multipleOf: 8,
	}

	if *test {
		genA.value = 65
		genB.value = 8921
	}

	var count int
	var elapsed time.Duration

	// if buffer < 0, calculate pairs sequentially
	// otherwise use some go channel magic
	if *buffer < 0 {
		start := time.Now()
		count = calculateSequentially(genA, genB)
		elapsed = time.Since(start)

	} else {
		start := time.Now()
		count = calculateConcurrently(genA, genB, *buffer)
		elapsed = time.Since(start)
	}

	fmt.Println("Total count:", count)
	fmt.Println("Elapsed time:", elapsed)
}
