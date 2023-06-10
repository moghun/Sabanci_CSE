;- Procedure: main-procedure
;- Input : Takes only one parameter named tripleList
;- Output : Returns list of triples according to the scenario
; described in section 3.
; Returns an error if the given parameter is not a tripleList.

(define main-procedure
    (lambda (tripleList)
        (if (or (null? tripleList) (not (list? tripleList)))
            (error "ERROR305: the input should be a list full of triples")
            (if (check-triple? tripleList)
                (sort-area (filter-pythagorean (filter-triangle
                (sort-all-triples tripleList))))
                (error "ERROR305: the input should be a list full of triples")
) )
) )



;- Procedure: check-triple?
;- Input : Takes only one parameter named tripleList
;- Output : Returns true if the given parameter consists of triples,
; returns false if otherwise.

(define check-triple?
    (lambda (tripleList)
        (cond
            (
                (null? tripleList) #t
            )
        (
            (not (check-length? (car tripleList) 3)) #f
        )
        (
            (not (check-sides? (car tripleList))) #f
        )
        (
            else 
            (
                check-triple? (cdr tripleList)
            )
        )
      )
) )



;- Procedure: check-length?
;- Input : Takes two parameters as inTriple and count
;- Output : Returns true if the length of the given list
; equals to count, returns false if otherwise.

(define check-length?
    (lambda (inTriple count)
        (cond
            (
                (null? inTriple) (zero? count)
            )
            (
                (check-length? (cdr inTriple) (- count 1))
            )
            (
                else #f
            )
        )
) )


;- Procedure: check-sides?
;- Input : Takes only one parameter named inTriple
;- Output : It returns true if all of the elements in the given
; list are numbers and each of the numbers is greater than zero.
; It returns false if otherwise.

(define check-sides?
    (lambda (inTriple)
        (and
            (number? (car inTriple))
            (number? (cadr inTriple))
            (number? (caddr inTriple))
            (> (car inTriple) 0)
            (> (cadr inTriple) 0)
            (> (caddr inTriple) 0)
        )
) )

;- Procedure: sort-all-triples
;- Input : Takes only one parameter named tripleList
;- Output : Returns the list of triples given as the parameter in which
; all triples are sorted internally in ascending order.

(define sort-all-triples
        (lambda (tripleList)
            (map sort-triple tripleList)
) )


;- Procedure: sort-triple
;- Input : Takes only one parameter named inTriple
;- Output : It returns the sorted inTriple in ascending order.

(define sort-triple
    (lambda (inTriple)
        (sort inTriple <)
) )


;- Procedure: filter-triangle
;- Input : Takes only one parameter named tripleList
;- Output : It returns tripleList consists of triples that each triple represents
; a triangle. So, it filters triangles in intripleList and discards other triples.

(define filter-triangle
    (lambda (tripleList)
        (cond
            (
                (null? tripleList) '()
            )
            (
                (triangle? (car tripleList)) (cons (car tripleList) (filter-triangle (cdr tripleList)))
            )
            (
                else
                (
                    filter-triangle (cdr tripleList)
                )
            )
        )
) )


;- Procedure: triangle?
;- Input : Takes only one parameter named triple
;- Output : It returns true if the given triple satisfies the triangle rule,
; returns false if otherwise.

(define triangle?
    (lambda (triple)
    (if (and
            (> (car triple) 0)
            (> (cadr triple) 0)
            (> (caddr triple) 0)
        )
    (> (+ (car triple) (cadr triple)) (caddr triple))
        #f)
) )

;- Procedure: filter-pythagorean
;- Input : Takes only one parameter named tripleList
;- Output : It returns tripleList consists of triples that each triple represents
; a pythagorean triangle. So, it filters pythagorean triangles in intripleList
; and discards other triples.

(define filter-pythagorean
     (lambda (tripleList)
       (cond
            (
                (null? tripleList) '()
            )
            (
                (pythagorean-triangle? (car tripleList)) (cons (car tripleList) (filter-pythagorean (cdr tripleList)))
            )
            (
                else
                (
                    filter-pythagorean (cdr tripleList)
                )
            )
        )
) )


;- Procedure: pythagorean-triangle?
;- Input : Takes only one parameter named triple
;- Output : It returns true if the given triple satisfies the Pythagorean theorem,
; returns false if otherwise.

(define pythagorean-triangle?
    (lambda (triple)
        (=
            (+ 
                (* (car triple) (car triple)) (* (cadr triple) (cadr triple))
            )
            (* (caddr triple) (caddr triple))
        )
) )


;- Procedure: sort-area
;- Input : Takes only one parameter named tripleList
;- Output : Returns the list of triples given as the parameter in which
; all triples are sorted according to the areas of the pythagorean triangles
; in ascending order.

(define sort-area
      (lambda (tripleList)
        (sort 
            tripleList compare-area
        )
       
) )

(define compare-area
    (lambda (triple-a triple-b)
        (< (get-area triple-a) (get-area triple-b))
) )


;- Procedure: get-area
;- Input : Takes only one parameter named triple
;- Output : It returns the area of the given pythagorean triangle.

(define get-area
   (lambda (triple)
    (* 
        (* (car triple) (cadr triple)) 0.5
    )
) )