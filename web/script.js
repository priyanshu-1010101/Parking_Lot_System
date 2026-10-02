class Vehicle { constructor(plate, type) { this.plate = plate; this.type = type; } }
class Car extends Vehicle { constructor(p) { super(p, "Car"); } }
class Bike extends Vehicle { constructor(p) { super(p, "Bike"); } }
class Truck extends Vehicle { constructor(p) { super(p, "Truck"); } }
class VehicleFactory {
    static create(type, plate) {
        if (type === "Car") return new Car(plate);
        if (type === "Bike") return new Bike(plate);
        if (type === "Truck") return new Truck(plate);
        throw new Error("Unknown vehicle type");
    }
}
class ParkingSpot {
    constructor(id, type) { 
        this.id = id; 
        this.type = type; 
        this.occupied = false; 
        this.vehicle = null; 
    }
    isFree() { return !this.occupied; }
    occupy(vehicle) { 
        this.occupied = true; 
        this.vehicle = vehicle; 
    }
    vacate() { 
        this.occupied = false; 
        this.vehicle = null; 
    }
}
class ParkingFloor {
    constructor(number) { this.number = number; this.spots = []; }
    addSpot(spot) { this.spots.push(spot); }
    findFreeSpot(type) { return this.spots.find(s => s.type === type && s.isFree()) || null; }
    status() {
        const out = {};
        for (const s of this.spots) {
            out[s.type] = out[s.type] || { occ: 0, total: 0 };
            out[s.type].total++;
            if (!s.isFree()) out[s.type].occ++;
        }
        return out;
    }
}
class Ticket {
    constructor(id, vehicle, spot, floor) {
        this.id = id; 
        this.vehicle = vehicle; 
        this.spot = spot; 
        this.floor = floor; 
        this.entry = Date.now();
    }
}
class HourlyPricing {
    fee(type, minutes) {
        const hours = Math.max(1, Math.ceil(minutes / 60));
        return hours * { Bike: 20, Car: 50, Truck: 100 }[type];
    }
}
class ParkingLot {
    static getInstance() {
        if (!ParkingLot.instance) ParkingLot.instance = new ParkingLot();
        return ParkingLot.instance;
    }
    constructor() { this.floors = []; this.tickets = new Map(); this.counter = 1000; this.pricing = new HourlyPricing(); this.justParked = null; }
    getFloor(n) { return this.floors.find(f => f.number === n) || null; }
    addFloor(n) {
        if (this.getFloor(n)) return `[ERROR] Floor ${n} already exists.`;
        this.floors.push(new ParkingFloor(n));
        this.floors.sort((a, b) => a.number - b.number); // -1, 0, 1, 2 ...
        return `[OK] Floor ${n} added.`;
    }
    addSpot(n, id, type) {
        const floor = this.getFloor(n);
        if (!floor) return `[ERROR] Floor ${n} does not exist. Add it first.`;
        floor.addSpot(new ParkingSpot(id, type));
        return `[OK] ${type} spot ${id} added to floor ${n}.`;
    }
    park(vehicle) {
        for (const floor of this.floors) {
            const spot = floor.findFreeSpot(vehicle.type);
            if (spot) {
                spot.occupy(vehicle);
                this.justParked = spot;
                const id = "T" + (++this.counter);
                this.tickets.set(id, new Ticket(id, vehicle, spot, floor));
                return `[ENTRY] ${vehicle.type} (${vehicle.plate}) parked at Floor ${floor.number}, Spot ${spot.id}\n        Ticket ID: ${id}`;
            }
        }
        return `[ERROR] No free ${vehicle.type} spot. ${vehicle.plate} was turned away.`;
    }
    unpark(ticketId) {
        const t = this.tickets.get(ticketId);
        if (!t) return `[ERROR] No active ticket ${ticketId}.`;
        const minutes = Math.floor((Date.now() - t.entry) / 60000);
        const fee = this.pricing.fee(t.vehicle.type, minutes);
        t.spot.vacate();
        this.tickets.delete(ticketId);
        return `[EXIT] ${t.vehicle.type} (${t.vehicle.plate}) left Spot ${t.spot.id}\n       Duration: ${minutes} minutes\n       Fee charged: Rs.${fee}`;
    }
    occupancy() {
        if (!this.floors.length) return "No floors yet. Click 'Add floor' to start.";
        let out = "----- Current Occupancy -----";
        for (const f of this.floors) {
            out += `\nFloor ${f.number}:`;
            const st = f.status();
            const types = Object.keys(st);
            if (!types.length) out += "\n  (no spots yet)";
            for (const t of types) out += `\n  ${t} spots: ${st[t].occ}/${st[t].total} occupied`;
        }
        return out;
    }
}

const lot = ParkingLot.getInstance();
const screen = document.getElementById("screen");
const input = document.getElementById("input");
const lotView = document.getElementById("lot");
const ICON = { Bike: "🏍️", Car: "🚗", Truck: "🚛" };
let flow = null;

function print(text, cls) {
    if (!cls) cls = /^\[(ERROR)\]/.test(text) ? "err" : /^\[(OK|ENTRY|EXIT)\]/.test(text) ? "ok" : "";
    const line = document.createElement("div");
    if (cls) line.className = cls;
    line.textContent = text;
    screen.appendChild(line);
    screen.scrollTop = screen.scrollHeight;
}

function render() {
    let total = 0, occ = 0;
    lotView.innerHTML = "";
    if (!lot.floors.length) {
        lotView.innerHTML = '<div class="empty">No floors yet. Click <b>Add floor</b> to start building your lot.</div>';
    }
    for (const f of lot.floors) {
        const used = f.spots.filter(s => s.occupied).length;
        total += f.spots.length; occ += used;
        const box = document.createElement("div");
        box.className = "floor";
        box.innerHTML = `<h3>Floor ${f.number}<small>${used}/${f.spots.length} occupied</small></h3>`;
        const bays = document.createElement("div");
        bays.className = "bays";
        if (!f.spots.length) bays.innerHTML = '<small>No spots yet. Click Add spot.</small>';
        for (const s of f.spots) {
            const b = document.createElement("div");
            b.className = "bay" + (s.occupied ? " occupied" : "") + (s === lot.justParked ? " just" : "");
            b.title = s.occupied ? `${s.vehicle.type} ${s.vehicle.plate}` : `Free ${s.type} spot`;
            const icon = document.createElement("span"); icon.className = "icon"; icon.textContent = ICON[s.type];
            const id = document.createElement("span"); id.className = "id"; id.textContent = s.id;
            b.append(icon, id);
            if (s.occupied) {
                const p = document.createElement("span"); p.className = "plate"; p.textContent = s.vehicle.plate;
                b.append(p);
            }
            bays.appendChild(b);
        }
        box.appendChild(bays);
        lotView.appendChild(box);
    }
    lot.justParked = null;
    document.getElementById("sTotal").textContent = total;
    document.getElementById("sFree").textContent = total - occ;
    document.getElementById("sOcc").textContent = occ;
}

const asNumber = v => /^-?\d+$/.test(v) ? +v : null; 
const asType = v => ({ "1": "Bike", "2": "Car", "3": "Truck" })[v] || null;
const asText = v => v.toUpperCase();
function start(steps, done) { flow = { steps, i: 0, data: {}, done }; ask(); }
function ask() { print("> " + flow.steps[flow.i].q, "ask"); input.focus(); }
function submit() {
    const v = input.value.trim();
    input.value = "";
    if (!v) return;
    if (!flow) { print("Click a button first.", "err"); return; }
    print("  " + v, "echo");
    const step = flow.steps[flow.i];
    const parsed = step.parse(v);
    if (parsed === null) { print("  That isn't valid. " + step.hint, "err"); return; }
    flow.data[step.key] = parsed;
    if (++flow.i < flow.steps.length) { ask(); return; }
    const f = flow; flow = null;
    print(f.done(f.data));
    render();
}
input.addEventListener("keydown", e => { if (e.key === "Enter") submit(); });

const typeQ = "Vehicle type? 1 = Bike, 2 = Car, 3 = Truck";
const typeHint = "Enter 1, 2 or 3.";
document.getElementById("bFloor").onclick = () =>
    start([{ key: "n", q: "Floor number? (0 = ground, -1 = basement)", parse: asNumber, hint: "Enter a whole number like 0, 1 or -1." }],
        d => lot.addFloor(d.n));
document.getElementById("bSpot").onclick = () =>
    start([
        { key: "n", q: "Which floor number? (0 = ground, -1 = basement)", parse: asNumber, hint: "Enter a whole number like 0, 1 or -1." },
        { key: "id", q: "Spot ID? (example: C-01)", parse: asText, hint: "" },
        { key: "type", q: "Spot type? 1 = Bike, 2 = Car, 3 = Truck", parse: asType, hint: typeHint }
    ], d => lot.addSpot(d.n, d.id, d.type));
document.getElementById("bPark").onclick = () =>
    start([
        { key: "plate", q: "License plate? (example: KA-01-HH-1234)", parse: asText, hint: "" },
        { key: "type", q: typeQ, parse: asType, hint: typeHint }
    ], d => lot.park(VehicleFactory.create(d.type, d.plate)));
document.getElementById("bUnpark").onclick = () =>
    start([{ key: "id", q: "Ticket ID? (example: T1001)", parse: asText, hint: "" }],
        d => lot.unpark(d.id));
document.getElementById("bStatus").onclick = () => { flow = null; print(lot.occupancy()); };
document.getElementById("bClear").onclick = () => { flow = null; screen.textContent = ""; };

print("PARKING LOT SYSTEM READY");
print("Start with 'Add floor', then 'Add spot', then 'Park vehicle'.\n");
render();