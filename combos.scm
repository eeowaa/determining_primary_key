(define join
  (lambda (x y)
    (cond
      ((null? x) y)
      (else (cons (car x) (join (cdr x) y))))))
(display (join '("foo" "bar") '("baz" "quux")))
(newline)

(define combos
  (lambda (l)
    (cond
      ((null? l) (list l))
      (else
        ((lambda (r)
           (join (map (lambda (q) (cons (car l) q)) r) r))
         (combos (cdr l)))))))
(display (combos '(a b c d)))
(newline)
