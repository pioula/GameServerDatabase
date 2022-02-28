import React from 'react';
import {fetchTable, fetchTableByObjectName, postObject, removeObject} from "../utils/fetch_utils";
import {Button, Col, Container, Form, FormControl, InputGroup, Modal, Row, Stack, Table} from "react-bootstrap";
import {SingleInput, updateFromSingleInput} from "../utils/class_utils";

const ranksURI = 'rankings';

class RanksTable extends React.Component {
    constructor(props) {
        super(props);
    }

    async onRemove(id) {
        await this.props.removeRank(id);
    }

    render() {
        const ranksTable = this.props.ranks.map(rank =>
        <tr key={rank.id}>
            <td><Button variant={"danger"} size={"sm"} onClick={() => this.onRemove(rank.id)}>Remove</Button></td>
            <td onClick={() => this.props.changeRank(rank.name, rank.formula)}>{rank.name}</td>
            <td onClick={() => this.props.changeRank(rank.name, rank.formula)}>{rank.base}</td>
        </tr>);
        return (
            <Table striped bordered hover>
                <thead>
                    <tr>
                        <th width={'7%'}/>
                        <th>Name</th>
                        <th>Base Value</th>
                    </tr>
                </thead>
                <tbody>
                    {ranksTable}
                </tbody>
            </Table>
        );
    }
}

class AddRank extends React.Component {
    resetStateQuery() {
        this.setState(prevState => ({
            ...prevState,
            query: {
                name: '',
                base: '',
                formula: ''
            }
        }));
    }

    constructor(props) {
        super(props);
        this.state = {
            query: {
                name: '',
                base: '',
                formula: ''
            },
            show: false,
            validated: false
        }

        this.updateFromChildSingleInput = this.updateFromChildSingleInput.bind(this);
        this.handleShow = this.handleShow.bind(this);
        this.handleClose = this.handleClose.bind(this);
        this.handleSubmit = this.handleSubmit.bind(this);
        this.handleFormula = this.handleFormula.bind(this);
    }

    updateFromChildSingleInput(singleInput, valueName) {
        this.setState(prevState => ({
            ...prevState,
            query: updateFromSingleInput(this.state.query, singleInput, valueName)
        }));
    }

    handleClose() {
        this.setState(prevState => ({
            ...prevState,
            show: false
        }));
        this.resetStateQuery();
    }

    handleShow() {
        this.setState(prevState => ({
            ...prevState,
            show: true,
            validated: false
        }));
        this.resetStateQuery();
    }

    async handleSubmit(e) {
        e.preventDefault();
        const form = e.currentTarget;
        if (form.checkValidity() === false) {
            e.stopPropagation();
            this.setState(prevState => ({
                ...prevState,
                validated: true
            }));
        } else {
            const newRank = {
                name: this.state.query.name,
                base: this.state.query.base,
                formula: this.state.query.formula,
            }

            this.props.addRank(newRank);
            this.handleClose();
        }
    }

    handleFormula(e) {
        this.state.query.formula = e.target.value;
    }

    render() {
        return (
            <>
                <Button variant={"success"} onClick={this.handleShow}>
                    Add Ranking
                </Button>
                <Modal size={"lg"} show={this.state.show} onHide={this.handleClose}>
                    <Modal.Header closeButton>
                        <Modal.Title>Add Ranking</Modal.Title>
                    </Modal.Header>
                    <Form noValidate validated={this.state.validated} onSubmit={this.handleSubmit}>
                        <Modal.Body>
                            <SingleInput
                                updateParent={this.updateFromChildSingleInput}
                                valueName={'name'}
                                valueTitle={'Ranking Name'}
                                required={true}/>
                            <SingleInput
                                updateParent={this.updateFromChildSingleInput}
                                valueName={'base'}
                                valueTitle={'Base Value'}
                                type={"number"}
                                required={true}/>
                            <Form.Group className="mb-3">
                                <Form.Label>Formula</Form.Label>
                                <Form.Control
                                    as="textarea"
                                    rows={3}
                                    onChange={this.handleFormula}
                                    required={true}/>
                            </Form.Group>
                        </Modal.Body>
                        <Modal.Footer>
                            <Button variant={"secondary"} onClick={this.handleClose}>
                                Close
                            </Button>
                            <Button variant={"primary"} type={"submit"}>
                                Add
                            </Button>
                        </Modal.Footer>
                    </Form>
                </Modal>
            </>
        );
    }
}

class SearchRank extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            query: ''
        }

        this.onChange = this.onChange.bind(this);
        this.onSearch = this.onSearch.bind(this);
    }

    onChange(e) {
        this.setState(prevState => ({
            ...prevState,
            query: e.target.value
        }));
    }

    async onSearch(e) {
        e.preventDefault();
        const query = this.state.query;
        this.setState(prevState => ({
            ...prevState,
            query: ''
        }));

        const ranks = await fetchTableByObjectName('/' + ranksURI + '/get-ranks-by-name', query);
        this.props.updateRank(ranks);
    }

    render() {
        return (
            <InputGroup className="mb-3">
                <FormControl
                    placeholder="Search Rank"
                    aria-describedby="basic-addon2"
                    value={this.state.query}
                    onChange={this.onChange}
                />
                <Button variant="primary" onClick={this.onSearch}>
                    Search
                </Button>
            </InputGroup>
        );
    }
}

class Ranks extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            ranks: [],
            rankFormula: {
                formula: '',
                name: 'Formula'
            }
        }

        this.changeRank = this.changeRank.bind(this);
        this.updateRank = this.updateRank.bind(this);
        this.removeRank = this.removeRank.bind(this);
        this.addRank = this.addRank.bind(this);
    }

    async updateRank(ranks) {
        this.setState(prevState => ({
            ...prevState,
            ranks: ranks
        }))
    }

    async removeRank(id) {
        await removeObject(ranksURI, id);
        await this.updateRank(await this.getRanks());
    }

    async getRanks() {
        return await fetchTable(ranksURI);
    }

    async componentDidMount() {
        await this.updateRank(await this.getRanks());
    }

    async addRank(newRank) {
        await this.updateRank(await postObject(ranksURI, newRank));
    }

    changeRank(name, formula) {
        this.setState(prevState => ({
            ...prevState,
            rankFormula: {
                name: name,
                formula: formula
            }
        }));
    }

    render() {
        return (
            <>
                <Stack gap={2} className={"col-md-10 mx-auto"}>
                    <Container>
                        <Row>
                            <Col>
                                <h2>Rankings</h2>
                            </Col>
                            <Col md={"auto"}>
                                <SearchRank updateRank={this.updateRank} />
                            </Col>
                            <Col md={"auto"}>
                                <AddRank addRank={this.addRank}/>
                            </Col>
                        </Row>
                        <Row>
                            <Col md={"auto"}>
                                <Form.Group className="mb-3" controlId="exampleForm.ControlTextarea1">
                                    <Form.Label>{this.state.rankFormula.name}</Form.Label>
                                    <Form.Control as="textarea" rows={3} value={this.state.rankFormula.formula} readOnly/>
                                </Form.Group>
                            </Col>
                            <Col>
                                <RanksTable
                                    ranks={this.state.ranks}
                                    changeRank={this.changeRank}
                                    removeRank={this.removeRank}/>
                            </Col>
                        </Row>
                    </Container>
                </Stack>
            </>
        );
    }
}

export default Ranks;