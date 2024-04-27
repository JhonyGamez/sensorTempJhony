-- CreateTable
CREATE TABLE "datos" (
    "id" SERIAL NOT NULL,
    "nombre" TEXT NOT NULL,
    "correo" TEXT NOT NULL,
    "carne" TEXT NOT NULL,
    "Latitud" TEXT NOT NULL,
    "Longitud" TEXT NOT NULL,
    "Humedad" DOUBLE PRECISION NOT NULL,
    "Temperatura" DOUBLE PRECISION NOT NULL,

    CONSTRAINT "datos_pkey" PRIMARY KEY ("id")
);
