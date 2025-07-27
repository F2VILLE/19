const { Readable } = require('stream');
const { finished } = require('stream/promises');
const fs = require("fs")

const days = Array.from(Array(9).keys());

(async () => {

  for await (const day of days) {
    const fday = `http://nebjix.free.fr/42/d${("0" + day.toString()).slice(-2)}/d${("0" + day.toString()).slice(-2)}.fr.pdf`
    console.log("Fetching " + fday + "...")
    try {
      const r = await fetch(fday)
      fs.mkdirSync(`./d${("0" + day.toString()).slice(-2)}`)
      const wfs = fs.createWriteStream(`./d${("0" + day.toString()).slice(-2)}/${("0" + day.toString()).slice(-2)}.pdf`)
      await finished(Readable.fromWeb(r.body).pipe(wfs))
    }
    catch (e) {
      console.log(e)
    }
  }
})()
