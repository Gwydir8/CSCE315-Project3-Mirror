(TeX-add-style-hook
 "Design-Document"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("inputenc" "utf8") ("fontenc" "T1") ("ulem" "normalem")))
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperref")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperimage")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperbaseurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "nolinkurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "path")
   (TeX-run-style-hooks
    "latex2e"
    "article"
    "art10"
    "inputenc"
    "fontenc"
    "fixltx2e"
    "graphicx"
    "longtable"
    "float"
    "wrapfig"
    "rotating"
    "ulem"
    "amsmath"
    "textcomp"
    "marvosym"
    "wasysym"
    "amssymb"
    "capt-of"
    "hyperref")
   (LaTeX-add-labels
    "sec-1"
    "sec-2"
    "sec-3"
    "sec-4"
    "sec-4-1"
    "sec-4-1-1"
    "sec-4-1-2"
    "sec-4-2"
    "fig:servclie"
    "sec-4-2-1"
    "sec-4-2-2"
    "sec-5"
    "sec-5-1"
    "sec-5-2"
    "fig:circ"
    "sec-5-3"
    "sec-5-4"
    "sec-6"
    "sec-7"
    "sec-7-1"
    "sec-7-2"
    "sec-7-3"
    "sec-8")))

