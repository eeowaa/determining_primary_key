#!/usr/bin/perl -w
use strict;
use Data::Dumper;

sub combos(@);
sub combos(@) {
    my @list = @{$_[0]};
    if (@list < 1) {
        return @list;
    } else {
        return map { unshift @$_, $list[0] } combos \{@list[1 .. $#list]};
    }
}
my @result = &combos \@ARGV; # see perlsub(1)
print Dumper @result;

__END__
I like using functional programming languages to reason about and implement
solutions to problems involving recursions, so I wrote the `combos' function
in Scheme before writing it in Perl. The original solution is shown below:

(define combos
 (lambda (l)
  (cond
   ((<= (length l) 1) (list l))
   (else
    (map
     (lambda (_) (cons (car l) _))
     (combos (cdr l)))))))

(define map
 (lambda (f l)
  (cond
   ((null? l) '())
   (else (cons (f (car l)) (map f (cdr l)))))))
