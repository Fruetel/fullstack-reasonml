FROM alpine:3.11 as build

# Install Opam package manager
RUN apk add --update \
    ocaml ocaml-compiler-libs ocaml-ocamldoc ocaml-findlib opam \
    make m4 musl-dev
ENV OPAMYES=1
RUN opam init --auto-setup --disable-sandboxing
RUN eval $(opam env) && opam install opam-depext
RUN eval $(opam env) && opam depext  mirage mirage-unix
RUN eval $(opam env) && opam install mirage mirage-unix

# Build webserver
ADD ./ /src
WORKDIR /src
RUN eval $(opam env) && mirage configure -t unix && make depend && make
WORKDIR /

# Repackage in fresh alpine container
FROM alpine:3.11
RUN apk add --update gmp
COPY --from=build /src/_build/main.native /bin/server
ENTRYPOINT /bin/server --port 8080
EXPOSE 8080

