

## Extension vs Service

In Zen Plugin 1.0, an Extension and a Service was rather interchangable with a
few minor differences.  With 2.0, we are defining services to be a special type 
of extension.

Services are extensions that are also startup / shutdown participants and are
generally larger in scope than an extension.

The scope of a service implementation is generally multiple components, wheras
a non-service extension is generally just a single component.

