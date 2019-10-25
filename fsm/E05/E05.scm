#!/usr/bin/env sh
exec guile -L . -L modules -e "main" -s "$0" "$@"
!#

;; Пример реализации конечного автомата в функциональном стиле.

(use-modules (ice-9 textual-ports))

(define (fsm-skip-comment port)
  (let ((ch (read-char port)))
    (cond
      ((eof-object? ch)
       #t)
      ((char=? ch #\newline)
       (newline)
       (fsm-default port))
      (else
       (fsm-skip-comment port)))))

(define (fsm-default port)
  (let ((ch (read-char port)))
    (cond
     ((eof-object? ch)
      #t)
      ((char=? ch #\#)
       (fsm-skip-comment port))
      (else
       (display ch)
       (fsm-default port)))))

(define (main args)
  (fsm-default (current-input-port)))

;;; E05.scm ends here.
