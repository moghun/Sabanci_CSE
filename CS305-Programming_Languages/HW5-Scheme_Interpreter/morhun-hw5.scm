(define 
    get-operator (lambda (op-symbol)
    (cond
        ((equal? op-symbol '+) +)
        ((equal? op-symbol '-) -)
        ((equal? op-symbol '*) *)
        ((equal? op-symbol '/) /)
        (else #f)
        )
    )
)


(define get-value (lambda (var env)
    (cond
      ((null? env) "ERROR")
      ((equal? (caar env) var) (cdar env))
      ((not(equal? (caar env) '())) (get-value var (cdr env)))
      )
    )
)

(define extend-env (lambda (var val old-env)
      (cons (cons var val) old-env)
    )
)

(define 
    list-reverse
    (lambda (lst)
        (if (null? lst)
            '()
            (append (list-reverse (cdr lst)) (list (car lst)))
        )
    )
)

(define repl (lambda (env)
  (let* (
         ; first print out some prompt
         (dummy1 (display "cs305> "))

         ; READ an expression
         (expr (read))

         ; Form the new environment
         (new-env (if (define-expr? expr)
                      (extend-env (cadr expr) (cs305-interpret (caddr expr) env) env)
                      env))

         ; EVALuate the expression read
         (val (if (define-expr? expr)
                  (cadr expr)
                  (cs305-interpret expr env)))

         ; PRINT the value evaluated together
         ; with a prompt as MIT interpreter does
         (dummy2 (display "cs305: "))
         (dummy3 (display val))

         ; get ready for the next prompt
         (dummy4 (newline))
         (dummy4 (newline)))
     (repl new-env))))


(define correct-list? (
    lambda (e)
        (and 
            (list? e) 
            (list? (car e)) 
            (= (length (car e)) 2) 
            (symbol? (caar e))
            (or 
                (null? (cdr e)) 
                (correct-list? (cdr e))
            )
        )
    )
)

(define define-expr? (
    lambda (e)
        (and 
            (list? e) 
            (= (length e) 3) 
            (equal? (car e) 'define) 
            (symbol? (cadr e))
        )
    )
)

(define if? (
    lambda (e)
        (and 
            (list? e) 
            (equal? (car e) 'if) 
            (= (length e) 4)
        )
    )
)

(define cond-else? (
    lambda (e)
        (and 
            (equal? (length e) 2) 
            (list? (cadr e)) 
            (equal? (caadr e) 'else )
        )
    )
)

(define cond? (
    lambda (e)
        (and 
            (> (length e) 2) 
            (equal? (car e) 'cond )  
            (list? (cadr e)) 
            (3-way-else? e) 
            (2-way-else? (cdr e)) 
        )
    )
)

(define 3-way-else? (
    lambda (e)
        (equal? (caar (list-reverse e)) 'else)
    )
)

(define 2-way-else? 
    (lambda (e)
        (
            if(and (equal? (caar e) 'else ) (null? (cdr e))) 
                #t
                (
                    if(and (equal? (caar e) 'else ) (not (null? (cdr e)))) 
                        #f 
                        (2-way-else? (cdr e))
                )
        )
    )
)



(define let? (
    lambda (e)
        (and 
            (list? e)
            (equal? (car e) 'let) 
            (or 
                (equal? () (cadr e) ) 
                (correct-list? (cadr e))
            ) 
            (= (length e) 3)
        )
    )
)

(define letstar? (
    lambda (e)
        (and 
            (list? e) 
            (equal? (car e) 'let*) 
            (= (length e) 3) 
        )
    )
)

(define cs305-interpret (
    lambda (e env)
        (cond
            ((null? e) "()")

            ((number? e) e)

            ((symbol? e) (get-value e env))

            ((not (list? e)) "ERROR")

            ((if? e) 
                (if (not(equal? (cs305-interpret (cadr e) env) 0 ))
                    (cs305-interpret (caddr e) env)
                    (cs305-interpret (cadddr e) env)
                )
            )

            ((cond? e)
                (if
                    (not
                        (equal? (cs305-interpret (caadr e) env) 0 ))
                                (cs305-interpret (cadadr e) env)
                                (cs305-interpret(cons 'cond (cddr e)) env )
                )
            )

            ((cond-else? e)
                (cs305-interpret(cadadr e) env )
            )

            ((let? e)
                (let*
                    (
                        (params 
                            (map cs305-interpret (map cadr (cadr e)) 
                                (make-list (length (map cadr (cadr e))) env))
                        )
                    (newenv 
                        (append 
                            ( map cons (map car (cadr e)) params) env))
                    )
                    
                    (cs305-interpret (caddr e) newenv)
                )
            )

            ((letstar? e)
                    (cond
                        (
                            (eq? 
                                (length (cadr e)) 0) (cs305-interpret (list 'let '() (caddr e)) env)
                        )

                        (
                            (eq? 
                                (length (cadr e)) 1) (cs305-interpret (list 'let (cadr e) (caddr e)) env)
                        )

                        (else
                            (let*
                                (
                                    (par 
                                        (cs305-interpret (car (cdaadr e)) env)
                                    )

                                (
                                    newenv (cons (cons (caaadr e) par) env))
                                )

                                (cs305-interpret (list 'let* (cdadr e) (caddr e)) newenv)
                            )
                        )
                    )
            )

            ((get-operator(car e))

            (let 
                (
                    (operands (map cs305-interpret (cdr e) (make-list (length (cdr e)) env)))
                    (operator (get-operator (car e)))
                )
                (apply operator operands))
            )

            (else "ERROR")
        )
    )
)
(define cs305 (lambda () (repl '())))