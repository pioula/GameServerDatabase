function POST(object) {
    return {
        method: 'POST',
        headers: {
            'Accept': 'application/json',
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(object)
    };
}

const DELETE = {
    method: 'DELETE',
    headers: {
        'Accept': 'application/json',
        'Content-Type': 'application/json'
    }
}

const GET = {
    method: 'GET',
    headers: {
        'Accept': 'application/json',
        'Content-Type': 'application/json'
    }
}

// Returns the array of objects that are in tableName
async function fetchTable(tableName) {
    const response = await fetch('/' + tableName);
    return await response.json();
}

// Returns an object with "id"
async function fetchObject(tableName, id) {
    const response = await fetch('/' + tableName + '/' + id, GET);
    return await response.json();
}

// Posts object into tableName
async function postObject(tableName, object) {
    await fetch('/' + tableName + '/', POST(object));

    return await fetchTable(tableName);
}

// Removes an object from table
async function removeObject(tableName, primaryKey) {
    await fetch('/' + tableName + `/${primaryKey}`, DELETE);
}

// Returns all records from table that's name is like objectName (most likely contains)
async function fetchTableByObjectName(path, objectName) {
    const response = await fetch(path + '?name=' + objectName, GET);
    return await response.json();
}

// Stringify object into parameters for URI link
function getQueryPath(object) {
    let query = '';
    Object.entries(object).forEach(([key, value], i) => {
        i === 0 ? query += '?' + key + '=' + value : query += '&' + key + '=' + value
    });
    return query;
}

export {fetchTable, postObject, removeObject, fetchTableByObjectName, POST, DELETE, GET, getQueryPath, fetchObject};