const express = require('express'); 
const { PrismaClient } = require('@prisma/client');
require('dotenv').config();
const prisma = new PrismaClient();
const app = express();
const PORT = process.env.PORT;
app.use(express.json());

app.get('/users', async (req, res)=>{
    try{
        const users = await prisma.usuarios.findMany();
        res.json(users);

    }catch(error){
        console.error('error buscando usuarios:', error);
        res.status(500).send('error del serivor')
    }
});

app.post('/users', async (req, res)=>{
    const users = await prisma.usuarios.create({
        data: req.body
    })
    res.json(users);
});

app.post('/sensor', async (req, res)=>{
    const sensor = await prisma.sensor.create({
        data: req.body
    }) 
    res.json(sensor);
});

app.get('/sensor', async (req, res)=>{
    const sensor = await prisma.sensor.findMany();
    res.json(sensor);
})


app.get('/sensor2', async (req, res)=>{
    const count = await prisma.sensor.count()
    const sensor2 = await prisma.sensor.findUnique({
        where:{
            id: count
        }
    });
    
    res.json(sensor2);
})


app.get('/sensor3', async (req, res)=>{

    const sensor2 = await prisma.sensor.findMany({
        where:{
            device:"burn"
        }
    });
    
    res.json(sensor2);
})


////////////////////

app.get('/datos', async (req, res)=>{
    const datos = await prisma.datos.findMany();
    res.json(datos);
})

app.post('/datos', async (req, res)=>{
    const datos = await prisma.datos.create({
        data: req.body
    }) 
    res.json(datos);
});

app.listen(PORT, () => {
console.log(`Server is running on port ${PORT}`);
});

